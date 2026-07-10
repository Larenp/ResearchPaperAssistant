import os

# Force offline mode
os.environ["HF_HUB_OFFLINE"] = "1"
os.environ["TRANSFORMERS_OFFLINE"] = "1"

# pyrefly: ignore [missing-import]
from sentence_transformers import SentenceTransformer
# pyrefly: ignore [missing-import]
import torch
import sys
import warnings

warnings.filterwarnings("ignore")

device = "mps" if torch.backends.mps.is_available() else "cpu"

model = SentenceTransformer(
    "all-MiniLM-L6-v2",
    device=device
)

text = sys.argv[1]

embedding = model.encode(text)

for value in embedding:
    print(value)