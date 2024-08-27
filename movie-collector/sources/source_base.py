from abc import ABC, abstractmethod

class SourceBase(ABC):
    @abstractmethod
    def next_page(self, page_idx):
        pass
