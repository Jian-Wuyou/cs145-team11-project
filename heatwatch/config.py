# for local testing; do not upload actual credentials 
import os

MYSQL_DATABASE_USER = os.getenv("MYSQLUSER")
MYSQL_DATABASE_PASSWORD = os.getenv("MYSQLPASSWORD")
MYSQL_DATABASE_DB = os.getenv("MYSQLDATABASE")
MYSQL_DATABASE_HOST = os.getenv("MYSQLPORT")
MYSQL_DATABASE_PORT = os.getenv("MYSQLPORT")