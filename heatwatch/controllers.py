from flask import Blueprint, current_app, request

from heatwatch.database import Database

controllers = Blueprint("controllers", __name__)

@controllers.post("/update_db")
def post_readings():
    """ Receives data from the Arduino
    
    JSON body parameters:
    readings        array of ordered tuples
    readings[n][0]  Time. Uses current server time if null.
    readings[n][1]  Heat index
    readings[n][2]  Temperature
    readings[n][3]  Humidity
    """

    req = request.json
    current_app.logger.debug(f'/update_db JSON "{req}"')

    db: Database = current_app.config["DB"]
    try:
        db.insert(req["readings"])
    except:
        return {'success': False}, 400, {'ContentType':'application/json'}
    return {'success': True}, 200, {'ContentType':'application/json'} 

@controllers.post("/readings")
def get_readings():
    """ Retrieve rows from the database wherein the given columns fall
        within the range [min, max]
    
    JSON body   will be a dict of dicts wherein each entry is of the form
                "column": {
                    "min": ...,
                    "max": ...
                }
    
    Wherein,
    column      the name of the column (must be one of "time",
                "temperature", "humidity", or "heat_index")
    min         minimum value to include in filtered data. If None and
                column is "time", only returns up to 100 rows.
    max         maximum value to include in filtered data. If None and
                column is "time", only returns up to 100 rows.


    Response parameters

    """
    req = request.json
    current_app.logger.debug(f'/readings JSON "{req}"') # For testing/debugging purposes

    db: Database = current_app.config["DB"]
    result = db.filter_by(req, "readings")
    
    return {
        "last": result[-1][0] if result else None,
        "first": result[0][0] if result else None,
        "data": result
    }, 200, {'ContentType':'application/json'}

@controllers.post("/summary")
def get_summary():
    """ Retrieve rows from the database wherein the given columns fall
        within the range [min, max]
    
    JSON body   will be a dict of dicts wherein each entry is of the form
                "column": {
                    "min": ...,
                    "max": ...
                }
    
    Wherein,
    column      the name of the column (must be one of "time",
                "temperature", "humidity", or "heat_index")
    min         minimum value to include in filtered data. If None and
                column is "time", only returns up to 100 rows.
    max         maximum value to include in filtered data. If None and
                column is "time", only returns up to 100 rows.


    Response parameters

    """
    req = request.json
    current_app.logger.debug(f'/summary JSON "{req}"') # For testing/debugging purposes

    db: Database = current_app.config["DB"]
    result = db.filter_by(req, "summary")
    
    return {
        "last": result[-1][0] if result else None,
        "first": result[0][0] if result else None,
        "data": result
    }, 200, {'ContentType':'application/json'}