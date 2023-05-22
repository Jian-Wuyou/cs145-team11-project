from os import path

from flask import Flask

# Flask app
root_path = path.abspath(path.join(path.dirname(__file__), ".."))
app = Flask(__name__, root_path=root_path)

if __name__ == "__main__":
    app.run(debug=True)
