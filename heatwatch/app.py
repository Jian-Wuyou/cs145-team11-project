from flask import Flask
from .extensions import mysql

from . import init_routes

# Flask app
app = Flask(__name__)

app.config['MYSQL_DATABASE_USER'] = 'root'
app.config['MYSQL_DATABASE_PASSWORD'] = 'password'
app.config['MYSQL_DATABASE_DB'] = 'cs145_heathelm'
app.config['MYSQL_DATABASE_HOST'] = 'localhost'

mysql.init_app(app)

init_routes(app)

if __name__ == "__main__":
    app.run(debug=True)
