from time import time

from flask import current_app
from MySQLdb.connections import Connection
from MySQLdb.cursors import Cursor


class Database:
    def __init__(self, db: Connection):
        self.db: Connection = db
    
    def filter_by(self, filters: dict[str, dict]):
        """ Retrieve rows from the database wherein the given columns fall
            within the range [min, max]
        
        Keyword arguments:
        filters     will be a dict of dicts wherein each entry is of the form
                    "column": {
                        "min": ...,
                        "max": ...
                    }
        
        Wherein,
        column      the name of the column (must be one of "time",
                    "temperature", "humidity", or "heat_index")
        min         minimum value to include in filtered data. If unspecified and
                    column is "time", only returns up to 100 rows.
        max         maximum value to include in filtered data. If unspecified and
                    column is "time", only returns up to 100 rows.
        """
        limit = ""
        # If min time is unspecified
        if filters.get("time", {}).get("min") is None:
            limit = " LIMIT 100"
        
        # Set max to current time if unspecified
        filters.get("time", {}).setdefault("max", round(time()*1e3))

        ops = {"min": ">=", "max": "<="}
        where = []

        for col, f in filters.items():
            for op, v in f.items():
                where.append(f"{col} {ops[op]} {v}")

        query = ("SELECT time, heat_index, temperature, humidity FROM readings"
                f"{' WHERE ' if len(where) else ''}{' AND '.join(where)}"
                 " ORDER BY time"
                f"{limit}")
        current_app.logger.debug(f'Executing query "{query}"')
        c: Cursor = self.db.cursor()
        c.execute(query)
        result = c.fetchall()
        current_app.logger.debug(f'Received result "{result}"')
        return result


    def insert(self, rows: list[list[int | float]]):
        """Inserts rows into the database

        Keyword arguments:
        rows        will be an array of ordered tuples, wherein each tuple is
                    (time, heat_index, temperature, humidity) 
        """

        c: Cursor = self.db.cursor()
        current_app.logger.debug(f'Inserting into DB...')
        c.executemany("INSERT INTO readings (time, heat_index, temperature, humidity) "
                      "VALUES (%s, %s, %s, %s)", rows)
    