import os

from flask import Flask, Response

from heatwatch.extensions import mysql

from . import config, init_routes

# Flask app
app = Flask(__name__)

app.config['MYSQL_DATABASE_USER'] = config.MYSQL_DATABASE_USER
app.config['MYSQL_DATABASE_PASSWORD'] = config.MYSQL_DATABASE_PASSWORD
app.config['MYSQL_DATABASE_DB'] = config.MYSQL_DATABASE_DB
app.config['MYSQL_DATABASE_HOST'] = config.MYSQL_DATABASE_HOST

mysql.init_app(app)

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

domain = os.getenv("RAILWAY_STATIC_URL", default="localhost")
domain_url = f"http://{domain}:{port}"

@app.context_processor
def set_domain():
    return { "domain" : domain_url }

if __name__ == "__main__":
    app.run(debug=True, port=os.getenv("PORT", default=5000))
