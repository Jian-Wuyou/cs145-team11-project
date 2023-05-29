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

Next, install the requirements by running
```bash
pip install -r requirements.txt
pip install flask pymysql flask-mysql
```

To run the program in, execute the following command:
In Windows, execute the following:
```cmd
flask --app heatwatch/app run
```

## API endpoints

### `POST /update_db`

#### JSON body parameters
| Name | Type | Description |
|---|---|---|
| `time` | int | Epoch time (in ms) when reading was made. If null or unspecified, defaults to server time. |
| `HI` | int | Calculated heat index. If null or unspecified, is calculated from temperature and relative humidity. |
| `T`<br>(required) | int | Temperature. |
| `RH`<br>(required) | int | Relative humidity. |
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
