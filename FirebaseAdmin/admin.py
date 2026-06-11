import firebase_admin
from firebase_admin import credentials, db

# Fetch the service account key JSON file contents
cred = credentials.Certificate('temperat-fea82-firebase-adminsdk-gk4pn-3feb811dc0.secret.json')

# Initialize the app with a service account, granting admin privileges
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://temperat-fea82.firebaseio.com/'
})

# As an admin, the app has access to read and write all data, regardless of Security Rules
ref = db.reference('test2')
table_data = ref.get()
print(len(table_data))

# This finds any entries that have the second value reading == 185 which can occur from hardware issues and updates them to match the other sensors reading.

updates = {}
# deletes = {}

# for key, value in table_data.items():
#     new_key = key + "000"
#     updates[new_key] = value
#     deletes[key] = None

for key, value in table_data.items():
    if len(value) == 2:
        if value[1] == 185:
            updates[key] = [value[0], value[0]]

print(f"Preparing to update {len(updates)} records...")

# Write new values in batch (uncomment this part. Left commented for safety)
# ref.update(updates)
# print("New values written.")

# Delete old keys
# ref.update(updates)
# print("Old keys deleted.")

# print("Migration complete.")
