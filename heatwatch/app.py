from flask import Flask
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

if __name__ == "__main__":
    app.run(debug=True)
