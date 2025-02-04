FROM python:3.11.1

# ensure that the python output
#i.e the stdout and stderr streams are sent straight to terminal
ENV PYTHONUNBUFFERED 1

ARG DEV=false

COPY requirements.txt /home/requirements.txt
COPY ./script.sh /home/script.sh
COPY ./default.png /media/default.png

RUN chmod 755 /home/script.sh

EXPOSE 8300

WORKDIR /rest

CMD [ "bash", "/home/script.sh" ]
