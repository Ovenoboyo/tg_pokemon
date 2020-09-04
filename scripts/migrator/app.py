import os
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = os.environ['PG_CONN_STR']
MIGRATION_DIR = os.path.join('scripts/migrator/migrations')

db = SQLAlchemy(app)
migrate = Migrate(app, db, directory=MIGRATION_DIR)

class Pokemon(db.Model):
    id = db.Column(db.Integer, primary_key=True)