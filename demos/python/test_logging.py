import logging
 
logging.basicConfig(format="%(asctime)s %(levelname)s:%(message)s", datefmt="%Y/%m/%d %H:%M", level=logging.INFO)


logging.debug('This is a debug message')
logging.info('This is an info message')
logging.warning('This is a warning message')
logging.error('This is an error message')
logging.critical('This is a critical message')

