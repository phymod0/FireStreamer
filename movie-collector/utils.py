from urllib.parse import quote_plus

class URLQueryBuilder:
    def __init__(self, endpoint):
        self.__endpoint = endpoint
        self.__params = []

    def add_param(self, param_name, param_value):
        param_value = str(param_value)
        self.__params.append((quote_plus(param_name), quote_plus(param_value)))

    def with_param(self, param_name, param_value):
        self.add_param(param_name, param_value)
        return self

    def build(self):
        if not self.__params:
            return self.__endpoint
        else:
            url_params = [f"{name}={value}" for (name, value) in self.__params]
            return f"{self.__endpoint}?" + "&".join(url_params)
