from flask import Blueprint, render_template, current_app

views = Blueprint("views", __name__)

@views.get("/")
def view_index():
    return render_template("index.html", domain=current_app.config["DOMAIN"])
