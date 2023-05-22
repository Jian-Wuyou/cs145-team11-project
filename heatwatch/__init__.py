from flask import Flask

from .views import views
from .controllers import controllers

def init_routes(app: Flask):
    app.register_blueprint(views)
    app.register_blueprint(controllers)
