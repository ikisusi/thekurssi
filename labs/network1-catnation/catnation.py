from mitmproxy import http
from mitmproxy import ctx

class CatNation:
    def response(self, flow):
        with open('jquery.js') as f:
            self.jquery = f.read()

        ctx.log.debug("XXXXXXXXXXXXXXX " + str(flow.request))
        flow.response.headers['X-Cat-Nation'] = 'Yes!'

        if flow.request.path.startswith("/jquery"):
            ctx.log.debug("FOOOOOOOOOOOO")
            flow.response = http.HTTPResponse.make(
                200,
                self.jquery,
                {"Content-Type": "application/javascript; charset=utf-8"}
            )

def start():
    ctx.log.info("CATNATION")
    return CatNation()
