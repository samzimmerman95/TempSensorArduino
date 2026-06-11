import firebase_admin
from firebase_admin import credentials, db

# Fetch the service account key JSON file contents
cred = credentials.Certificate('temperat-fea82-firebase-adminsdk-gk4pn-97d4eda3b1.secret.json')

# Initialize the app with a service account, granting admin privileges
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://temperat-fea82.firebaseio.com/'
})

lake_ref = db.reference("lake23")
data = lake_ref.get()

if not data:
    print("No data found in /lake23.")
    exit()

reordered_data = {}

for key, values in data.items():
    if isinstance(values, list) and len(values) == 5:
        reordered = [values[2], values[4], values[1], values[3], values[0]]
        reordered_data[key] = reordered
    else:
        print(f"Skipping key {key}: not a list of 5 items.")

# Overwrite with reordered data
lake_ref.set(reordered_data)
print("Reordering complete.")