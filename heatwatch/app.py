from flask import Flask, Response

from . import init_routes

# Flask app
app = Flask(__name__)

init_routes(app)

@app.after_request
def add_cors(resp: Response):
    # Allow all domains for now
    resp.headers.update({
        "Access-Control-Allow-Origin": "*",
        "Access-Control-Allow-Methods": "GET, POST, OPTIONS, PUT, DELETE",
        "Access-Control-Allow-Headers": "Content-Type, Access-Control-Allow-Headers, X-Requested-With"
    })
    return resp

if __name__ == "__main__":
    app.run(debug=True)
