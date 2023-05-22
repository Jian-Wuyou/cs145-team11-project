from flask import Blueprint, render_template

views = Blueprint("views", __name__)

@views.get("/")
def view_index():
    return render_template("index.html")
