from flask import Flask

from . import init_routes

# Flask app
app = Flask(__name__)

init_routes(app)

if __name__ == "__main__":
    app.run(debug=True)
