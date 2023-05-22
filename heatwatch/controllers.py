from flask import Blueprint, request

controllers = Blueprint("controllers", __name__)

@controllers.post("/readings")
def post_readings():
    """Receives data from the Arduino"""
    print(request.get_data(as_text=True))
    return '{"success": true}', 200

@controllers.get("/readings")
def get_readings():
    """Sends readings in JSON format"""
    return {
        "testing": "success"
    }