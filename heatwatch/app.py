import os

import mariadb
from dotenv import load_dotenv
from flask import Flask, Response

from heatwatch import init_routes
from heatwatch.database import Database

load_dotenv()

# Create Flask app
app = Flask(__name__)

# Check domain
port = os.getenv("FLASK_RUN_PORT") or os.getenv("PORT", 29002)
domain = os.getenv("RAILWAY_STATIC_URL", "localhost")
domain_url = f"https://{domain}" if domain != "localhost" else f"http://localhost:{port}"

app.config["DOMAIN"] = domain_url

# Initialize routes
init_routes(app)

db = mariadb.connect(
    host=os.getenv("DB_HOST"),
    user=os.getenv("DB_USERNAME"),
    password=os.getenv("DB_PASSWORD"),
    database=os.getenv("DB_DATABASE"),
    autocommit=True,
    ssl_verify_cert=True,
    ssl=True,
    ssl_ca="/etc/ssl/certs/ca-certificates.crt"
)

app.config["DB"] = Database(db)

# Add CORS headers
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
    app.run("0.0.0.0", port, debug=True)
