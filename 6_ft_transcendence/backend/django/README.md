# Django

This repository is for django app

## QuickStart

There is a `docker-compose.yml` file in the parent folder. You can just run:

```bash
make
```

which runs Docker Compose service `backend`, and follow logs of the service.

After that, you can connect to website `http://localhost:8000/admin` or something.

If you want to run the server in your local environment, you have to install required packages. It is recommended to install virtual environment.

```bash
python -m venv .venv
. .venv/bin/activate
which pip # Should point inside of .venv folder

pip install -r requirements.txt
python manage.py migrate
python manage.py runserver 0.0.0.0:8000
```

Now you can connect to `http://localhost:8000/admin` or something.

## TODO

-[ ] Split Django app into multiple container (MSA)
-[ ] Construct multiple apis
-[ ] OpenAPI docs
-[ ] 2FA (with Google Authenticator)
-[ ] JWT (JSON Web Token)
-[ ] Basic Authenticate
-[ ] Live Chat (w/ WebSocket)