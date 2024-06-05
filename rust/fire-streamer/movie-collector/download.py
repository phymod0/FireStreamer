from enum import Enum, auto

class Quality(Enum):
    RES_720P = auto()
    RES_1080P = auto()
    RES_2160P = auto()
    RES_3D = auto()

def get_quality_by_name(name):
    name = f"RES_{name.strip().upper()}"
    return getattr(Quality, name)

class Download:
    def __init__(self,
                 quality,
                 size_bytes,
                 magnet_link,
                 seeder_count,
                 peer_count):
        self.quality = quality
        self.size_bytes = size_bytes
        self.magnet_link = magnet_link
        self.seeder_count = seeder_count
        self.peer_count = peer_count

    def debug(self, indent=4):
        indent = " " * indent
        result = ""
        result += f"[{self.magnet_link}]\n"
        result += f"{indent}Quality: {self.quality}\n"
        result += f"{indent}Size (bytes): {self.size_bytes}\n"
        result += f"{indent}Seeders/peers: {self.seeder_count} / {self.peer_count}"
        return result

class DownloadBuilder:
    def __init__(self):
        self.__quality = None
        self.__size_bytes = None
        self.__magnet_link = None
        self.__seeder_count = None
        self.__peer_count = None

    def set_quality(self, quality):
        self.__quality = get_quality_by_name(quality)

    def set_size_bytes(self, size_bytes):
        self.__size_bytes = int(size_bytes)

    def set_magnet_link(self, magnet_link):
        self.__magnet_link = magnet_link

    def set_seeder_count(self, seeder_count):
        self.__seeder_count = int(seeder_count)

    def set_peer_count(self, peer_count):
        self.__peer_count = int(peer_count)

    def build(self):
        return Download(
            self.__quality,
            self.__size_bytes,
            self.__magnet_link,
            self.__seeder_count,
            self.__peer_count
        )
