# cs145-team11-project

## Setup

First, create the python virtual environment using the `virtualenv` module.

```bash
pip install virtualenv
python -m venv venv
```

In Linux, start the virtual environment by running

```bash
source ./venv/bin/activate
```

Or, in Windows, by running

```bash
.\venv\Scripts\activate
```

Next, install the requirements by running either of the following:

```bash
sudo apt-get install python3-dev python3.11-dev default-libmysqlclient-dev build-essential # On Linux
pip install wheel
pip install flask mysqlclient python-dotenv
```

To run the program in debug mode, execute the following command:
```bash
python -m heatwatch.app
```

To run it in production mode, execute the following
```cmd
FLASK_RUN_PORT=$PORT FLASK_RUN_HOST=0.0.0.0 flask --app heatwatch/app run
```

## Deployment

The webserver is currently being hosted on railway.app, and the database is hosted on planetscale.

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
