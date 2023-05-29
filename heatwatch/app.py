import os
from flask import Flask, Response
from .extensions import mysql

from . import init_routes
from . import config  

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

domain = os.getenv("RAILWAY_STATIC_URL", "localhost")
domain_url = f"http{'s' if domain != 'localhost' else ''}://{domain}"

if __name__ == "__main__":
    app.run("0.0.0.0", os.getenv("PORT", 5000), debug=True)
