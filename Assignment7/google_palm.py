import google.generativeai as palm

import textwrap
import numpy as np
import pandas as pd
import sys

# Read the API key from the command line
palm.configure(api_key = sys.argv[1])

    # Read the paragraphs from the files
texts = []

for i in range(int(sys.argv[2])):
  with open("paragraph_" + str(i) + ".txt", 'r') as f:
    texts.append(f.read())

palm.configure(api_key='AIzaSyDXDQjKj2bCdyLoXqKQC-H4hERF-ZakBEc')

models = [m for m in palm.list_models() if 'embedText' in m.supported_generation_methods]
model = models[0]


df = pd.DataFrame(texts)
df.columns = ['Text']


# Get the embeddings of each text and add to an embeddings column in the dataframe
def embed_fn(text):
  return palm.generate_embeddings(model=model, text=text)['embedding']

df['Embeddings'] = df['Text'].apply(embed_fn)

query = sys.argv[4]

def find_best_passage(query, dataframe):
  """
  Compute the distances between the query and each document in the dataframe
  using the dot product.
  """
  query_embedding = palm.generate_embeddings(model=model, text=query)
  dot_products = np.dot(np.stack(dataframe['Embeddings']), query_embedding['embedding'])
  idx = np.argmax(dot_products)
  return dataframe.iloc[idx]['Text'] # Return text from index with max value

passage = find_best_passage(query, df)

def make_prompt(query, relevant_passage):
  escaped = relevant_passage.replace("'", "").replace('"', "").replace("\n", " ")
  prompt = textwrap.dedent("""You are a helpful and informative bot that answers questions using text from the reference paragraphs included below. \
  Be sure to respond in a complete sentence, being comprehensive, including all relevant background information. \
  However, you are talking to a non-technical audience, so be sure to break down complicated concepts and \
  strike a friendly and converstional tone. \
  If the passage is irrelevant to the answer, you may ignore it.
  QUESTION: '{query}'
  PASSAGE: '{relevant_passage}'

    ANSWER:
  """).format(query=query, relevant_passage=escaped)

  return prompt

prompt = make_prompt(query, passage)
print(prompt)

text_models = [m for m in palm.list_models() if 'generateText' in m.supported_generation_methods]

text_model = text_models[0]

temperature = 0.5
answer = palm.generate_text(prompt=prompt,
                            model=text_model,
                            candidate_count=3,
                            temperature=temperature,
                            max_output_tokens=1000)
s = ""
for i, candidate in enumerate(answer.candidates):
  print(f"Candidate {i}: {candidate['output']}\n")
