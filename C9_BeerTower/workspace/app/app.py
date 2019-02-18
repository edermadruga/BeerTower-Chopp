import json

from flask import Flask, render_template, redirect, request
from flask_socketio import SocketIO, send, emit
from flask_cors import CORS

app = Flask(__name__)
#app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)
CORS(app)

estado = {
    "TEMPERATURA" : 0,
    "PAGAMENTO" : 0,
    "VALOR" : 0 ,
    "CHAMADO" : 0
    }
    
change = 0;

@app.route("/")
def rota_inicial():
    print(estado)
    return render_template("index.html",data=estado)
    
@app.route("/contato")
def rota_contato():
    return render_template("contato.html",data=estado)
    
@app.route("/portfolio")
def rota_portfolio():
    return render_template("portfolio.html",data=estado)


@app.route("/upload", methods=["POST"])
def rota_data():
    global estado
    estado = request.get_json()
    socketio.emit("atualiza",estado)
    return "ok"
    
@app.route("/download", methods=["GET"])
def rota_download():
    global estado
    global change
    if change == 1 :
        change = 0
        return json.dumps(estado)
    return "1";
    
    

@socketio.on('chamar_garçom')
def Chamar_garçom():
    global estado
    global change
    change = 1
    estado["CHAMADO"] = 1
    
@socketio.on('cancelar_garçom')
def Cancelar_chamada():
    global estado, change
    change = 1;
    estado["CHAMADO"] = 0




if __name__ == "__main__":
    app.run("0.0.0.0",port=8080)