# import numpy as np

# X_idx = np.arange(10)
# X = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
# for i in X_idx:
#   batch_idx = X_idx[i:i + 3]
#   start = batch_idx[0]
#   stop = batch_idx[-1]
#   batch = X[start:stop + 1]
#   X_idx = X_idx[i + 2:]
#   print(batch)


import nltk
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer

# nltk.download('stopwords')
# nltk.download('wordnet')
# nltk.download('omw-1.4')

eng_stopwords = set(stopwords.words('spanish'))
print(eng_stopwords)