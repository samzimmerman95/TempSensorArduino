import firebase_admin
from firebase_admin import credentials, db

# Fetch the service account key JSON file contents
cred = credentials.Certificate('temperat-fea82-firebase-adminsdk-gk4pn-97d4eda3b1.secret.json')

# Initialize the app with a service account, granting admin privileges
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://temperat-fea82.firebaseio.com/'
})

backup_ref = db.reference("test2-backup")
backup_ref.delete()


