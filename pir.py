import json
from flask import Flask, request, jsonify

app = Flask(__name__)

pir_DATA = []

@app.route("/")
def root_route():
    return "Hello world!"

@app.route("/pir")
def get_pir():
    return jsonify(pir_DATA)

@app.route("/submit-pir", methods=["POST"])
def post_pir():
    pesan = request.data.decode("utf8")
    pir_DATA.append(float(pesan))
    print(pesan)
    return f"Received pir {pesan}"

@app.route("/submit", methods=["POST"])
def post_data():
    pesan = request.data.decode("utf8")
    pesan = json.loads(pesan)
    pir_DATA.append(float(pesan["pir"]))
    print(pesan)
    return f"Received data {pesan}"

if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0')
