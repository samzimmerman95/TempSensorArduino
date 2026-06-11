import firebase_admin
from firebase_admin import credentials, db

# Fetch the service account key JSON file contents
cred = credentials.Certificate('temperat-fea82-firebase-adminsdk-gk4pn-97d4eda3b1.secret.json')

# Initialize the app with a service account, granting admin privileges
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://temperat-fea82.firebaseio.com/'
})

# Reference the source and destination
source_ref = db.reference("test2")
backup_ref = db.reference("test2-backup")

# Read from /test2
print("Reading data from /test2...")
data = source_ref.get()

if data is None:
    print("No data found in /test2.")
else:
    # Write to /test2-backup
    backup_ref.set(data)
    print("Backup completed to /test2-backup.")

