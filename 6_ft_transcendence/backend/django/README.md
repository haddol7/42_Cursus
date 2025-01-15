# Django

This repository is for django app

## QuickStart

There is a `docker-compose.yml` file in the parent folder. You can just run the following in the parent folder:

```bash
make
```

which runs Docker Compose service `backend`, and follow logs of the service.

After that, you can connect to website `http://localhost:8000/admin` or something.

If you want to run the server in your local environment, you have to install required packages. It is recommended to install packages in virtual environment.

```bash
python -m venv .venv
. .venv/bin/activate
which pip # Result of this command should point inside of .venv folder

pip install -r requirements.txt
python manage.py migrate
python manage.py runserver 0.0.0.0:8000
```

Now you can connect to `http://localhost:8000/admin` or something.

## TODO

- [ ] Split Django app into multiple container (MSA)
- [ ] Construct multiple apis
    - [ ] User
    - [ ] Auth
    - [ ] MatchMaking
    - [ ] Game History, Stats, etc.
    - Maybe more
- [ ] OpenAPI docs
- [ ] 2FA (with Google Authenticator)
- [ ] JWT (JSON Web Token)
- [ ] Basic Authenticate
- [ ] Live Chat (w/ WebSocket)

## Coding Convention

- In VSCode, Install extension `black formatter`
    - You can find it by searching `ms-python.black-formatter`
- If you are opening `django` folder(this folder!) with VSCode, that's ok
    - If not, you should open `Settings` and set the following:
        - `Format On Save`: `True`
        - `Default Formatter`: `Black Formatter`
        - `Python > Analysis > Type Checking Mode`: `standard`
        - `Python > Analysis > Diagnostic Mode`: `workspace`
- The following settings is NOT enforced, but you can choose to use them:
    - `Python > Analysis > Inaly Hints`: `True`
    - `Python > Analysis > Auto Format Strings`: `True`
    - `Python > Analysis > Auto Import Completions`: `True`
    - `Python > Analysis > Generate With Type Annotation`: `True`
- [Type hint](https://docs.python.org/ko/3.10/library/typing.html) should be annotated whenever it is appropriate
    - When variable is introduced as parameter, you MUST use type hint whenever it is possible
    - If return value of function has a type, you can choose not to use type hint, but you can choose to use it
        - `Inlay Hint` setting can help you this!
    - If you are doubt what type hint is, make sure to be familiar with the usage