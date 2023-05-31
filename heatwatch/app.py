import os

import MySQLdb
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

# Setup database
db = MySQLdb.connect(
    host=os.getenv("HOST"),
    user=os.getenv("USERNAME"),
    passwd=os.getenv("PASSWORD"),
    db=os.getenv("DATABASE"),
    autocommit=True,
    # ssl_mode="VERIFY_IDENTITY",
    # ssl={
    #     "ca": "/etc/ssl/cert.pem"
    # }
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
