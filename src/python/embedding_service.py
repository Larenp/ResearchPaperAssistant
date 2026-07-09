# pyrefly: ignore [missing-import]
from sentence_transformers import SentenceTransformer
import torch
import sys
import warnings
from urllib3.exceptions import NotOpenSSLWarning

warnings.filterwarnings("ignore", category=NotOpenSSLWarning)
warnings.filterwarnings("ignore", category=FutureWarning)
device = "mps" if torch.backends.mps.is_available() else "cpu"

model = SentenceTransformer("all-MiniLM-L6-v2", device=device)

text = sys.argv[1]

embedding = model.encode(text)

for value in embedding:
    print(value)