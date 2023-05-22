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

Next, install the requirements by running
```bash
pip install -r requirements.txt
```

To run the program, execute the following command:
```bash
uwsgi --ini uwsgi.ini
```

## API endpoints

### `POST /update_db`

#### JSON body parameters
| Name | Type | Description |
|---|---|---|
|  |  |  |
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
