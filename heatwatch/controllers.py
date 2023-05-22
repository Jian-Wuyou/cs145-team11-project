from time import time
from random import randint
from flask import Blueprint, request

controllers = Blueprint("controllers", __name__)

@controllers.post("/update_db")
def post_readings():
    """Receives data from the Arduino"""
    print(request.get_data(as_text=True)) # For testing/debugging purposes

    data = request.json

    if "T" not in data or "RH" not in data:
        return '{"success": false, "error": "Missing temperature/humidity."}', 400

    if "time" not in data or data["time"] == None:
        data["time"] = round(time() * 1000)
    
    if "HI" not in data:
        # Calculate heat index
        ...
    
    # Upload data to server

    return '{"success": true}', 200

@controllers.post("/readings")
def get_readings():
    """Sends readings in JSON format"""
    data = request.json

    if "from" not in data:
        return '{"success": false, "error": "Missing \'from\' parameter."}', 400

    # If `to` is not specified, set it to the current time
    if "to" not in data:
        data["to"] = round(time() * 1000)

    start, end = data["from"], data["to"]

    data = []
    # Generate fake data for testing
    for t in range(start+1, end+1, 200):
        data.append([t, randint(10, 100), 0, 0])

    return {
        "data" : data,
        "first" : start+1,
        "last" : t
    }