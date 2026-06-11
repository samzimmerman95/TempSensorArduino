```bash
# To create new venv if it does not exist
python3 -m venv venv
# To activate
source venv/bin/activate
# Install requirements
pip install -r requirements.txt

deactivate
```

First make a backup of any DB table that you are working on with `create-db-table-backup.py`. Delete if after you no longer need it with `delete-db-table-backup.py`
