from sentence_transformers import SentenceTransformer

model = SentenceTransformer("all-MiniLM-L6-v2")

text = input()

embedding = model.encode(text)

print(" ".join(map(str, embedding)))