import re
import sys

class MRM:
    METHOD = input()
    URL = input()
    GET = {name:value for couple in input().split("&") for name, _, value in [couple.partition("=")] if couple}
    request, _, CONTENT = sys.stdin.read().partition("\0")
    #print(request, file=sys.stderr)
    HEADERS = {}
    POST = ""
    is_header = True
    for line in request.split("\n"):
        if not line.strip():
            is_header = False
            continue
        if is_header:
            name, _, value = line.partition(":")
            HEADERS[name.strip()] = value.strip()
        else:
            POST += "\n"+line
    POST = POST[1:]
    
    chunks = re.split(r"<\?mrm\s(.*?)\?>", CONTENT, flags=re.DOTALL)
    chunk = None
    plain_text = True

    def get(name, or_else=None):
        return MRM.GET.get(name, or_else)


for MRM.chunk in MRM.chunks:
    if MRM.plain_text:
        print(MRM.chunk)
    else:
        exec(MRM.chunk)
    MRM.plain_text = not(MRM.plain_text)

#print("MARIMBA END", file=sys.stderr)
sys.exit(0)
