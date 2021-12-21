# HTTP server in C
A primitive web server in C. It accepts HTTP requests and can serve static files (html, images, videos...) as well as dynamic files, evaluated by a small python engine called *Marimba*. All requests are treated in parallel.

## Requests
This Web server ignores the mehtod used and treat the url as a relative path from the root directory. However, the method name, headers and body will be forwarded to Marimba in case it is a dynamic file.
By default the root directory is `html/`.


## Marimba
*Marimba* is an HTML renderer that generates dynamic content from mixed HTML/python3 files. The `.mrm` files have the same structure as regular `.html` files, but they can contain a new tag `<?mrm [...] ?>`. Here is a simple *hello world* with *Marimba*:
```html
<!DOCTYPE html>
<html lang="en">
	<head>
	        <meta charset="UTF-8">
	        <title>Marimba</title>
	</head>
	<body>
	        <h1><?mrm print("Hello world!") ?></h1>
	</body>
</html>
```
The python code found in `<?mrm ?>` tags is evaluated in order and with persisting memory (a variable declared in one block is still accessible in the following blocks). Each block is replaced with the content of the standard output.
*Marimba* provides a `MRM` object which contains:
* `METHOD`: the method used to request the file
* `URL`: the url used to request the file
* `GET`: a dictionary representing the content of the URN
* `POST`: the raw body of the request
* `content`: the raw content of the `.mrm` file
* `get(name, orElse)`: a function that returns the value of `name` if it is in `GET`, `orElse` otherwise

## Maracas
*Maracas* is a simple macro based logger used for colorful debugging and logging of this web server.
