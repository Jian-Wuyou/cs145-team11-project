# cs145-team11-project

## Setup

First, create the python virtual environment using the `virtualenv` module. On Windows, do the following:

```bash
pip install virtualenv
python -m venv venv
.\venv\Scripts\activate
```

In Linux, do the following:

```bash
sudo apt-get install python3-venv
python -m venv venv
source ./venv/bin/activate
```

Next, install the requirements by running either of the following:

```bash
pip install -r requirements.txt
```

```bash
sudo apt-get update
sudo apt-get install build-essential python3-dev ca-certificates libmariadb-dev gunicorn # On Linux
pip install flask python-dotenv gunicorn mariadb
```

To run the program in debug mode, execute either of the following commands (replace $PORT with the port number):
```bash
python -m heatwatch.app
FLASK_RUN_PORT=$PORT FLASK_RUN_HOST=0.0.0.0 flask --app heatwatch/app --debug run
```

To run it in production mode, execute the following
```cmd
gunicorn --workers=4 --access-logfile - --bind=0.0.0.0:$PORT heatwatch.app:app
```

## Deployment

The webserver is currently being hosted on heatwatch.up.railway.app, and the database is hosted on planetscale.

## API endpoints

### `POST /update_db`

#### JSON body parameters

| Name | Type | Description |
| --- | --- | --- |
| `readings`| array | Array of ordered tuples |
| `readings[n][0]` | int | Epoch time (in ms) when reading was made. If null or unspecified, defaults to server time. |
| `readings[n][1]` | float | Calculated heat index. If null or unspecified, is calculated from temperature and relative humidity. |
| `readings[n][2]`<br>(required) | float | Temperature. |
| `readings[n][3]`<br>(required) | int | Relative humidity. |

### `POST /readings`

#### JSON body parameters
| Name | Type | Description |
|---|---|---|
| `from`<br>(required) | int | Sends readings made after the epoch time (in ms) specified (exclusive). |
| `to`<br>(optional) | int | Sends readings made before the epoch time (in ms) specified (inclusive). |

#### Response fields
| Name | Type | Description |
|---|---|---|
| `last` | int | Epoch time (in ms) of last reading sent. |
| `first` | int | Epoch time (in ms) of first reading sent. |
| `data` | array | Array of tuples of readings in ascending order of time. |
| `data[n][0]` | int | Epoch time when reading was recorded. |
| `data[n][1]` | int | Calculated heat index. |
| `data[n][2]` | int | Temperature. |
| `data[n][3]` | int | Relative humidity. |
