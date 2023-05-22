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
