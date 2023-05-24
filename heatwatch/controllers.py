from time import time
from random import randint
from flask import Blueprint, request, jsonify
import pymysql
from .extensions import mysql

controllers = Blueprint("controllers", __name__)

@controllers.post("/update_db")
def post_readings():
    """Receives data from the Arduino"""

    #req = {"id":int,"time":int,"temperature":int,"humidity":int,"heatIndex":int}
    req = request.json
    print(request.get_data(as_text=True)) # For testing/debugging purposes

    if "T" not in req or "RH" not in req:
        return '{"success": false, "error": "Missing temperature/humidity."}', 400

    if "time" not in req or req["time"] == None:
        req["time"] = round(time() * 1000)
    
    if "HI" not in req:
        # Calculate heat index
        ...
        
    ## query DB
    try:
        conn = mysql.connect()
        cursor = conn.cursor(pymysql.cursors.DictCursor)
        sql = "INSERT INTO readings (id, `time`, temperature, humidity, `heat index`) VALUES (%s,%s,%s,%s,%s)"
        args=[req["id"],req["time"],req["T"],req["RH"],req["HI"]]
        cursor.execute(sql,args)  
        conn.commit()
        return '{"success": true}', 200

    except Exception as e:
        print(e)
        return '{"success": false}', 500

    finally:    
        cursor.close() 
        conn.close()

@controllers.post("/readings")
def get_readings():
    """Sends readings in JSON format"""
    data = request.json

    if "from" not in data:
        return '{"success": false, "error": "Missing \'from\' parameter."}', 400

    # If `to` is not specified, set it to the current time
    if "to" not in data:
        data["to"] = round(time() * 1000)

    id, start, end = data["id"], data["from"], data["to"]

    ## query DB
    try:
        conn = mysql.connect()
        cursor = conn.cursor(pymysql.cursors.DictCursor)
        sql="SELECT * FROM readings WHERE id = %s AND `time` > %s AND `time` <= %s ORDER BY `time`"
        args=[id, start, end]
        cursor.execute(sql,args)
        rows = cursor.fetchall() # result data

        first, last = 0,0
        if rows: # if not empty
            first,last = rows[0]["time"], rows[-1]["time"] # get time of first and last entry
        res = jsonify({'last':last, 'first':first, 'data': rows}) # return {last, first, data}
 
        return res, 200
    
    except Exception as e:
        print(e)
        return '{"success":false}', 500

    finally:
        cursor.close() 
        conn.close()

    # generate fake data in a separate script
    """
    # Generate fake data for testing
    for t in range(start+1, end+1, 200):
        data.append([t, randint(10, 100), 0, 0])

    return {
        "data" : data,
        "first" : start+1,
        "last" : t
    }
    """