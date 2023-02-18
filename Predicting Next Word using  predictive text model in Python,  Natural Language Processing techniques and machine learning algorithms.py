import nltk
from nltk.corpus import gutenberg
from nltk.tokenize import word_tokenize
from nltk import FreqDist
from nltk.util import ngrams
from collections import defaultdict

# load the data
nltk.download('gutenberg')
emma = gutenberg.raw('austen-emma.txt')

# tokenize the data
tokens = word_tokenize(emma)

# create a frequency distribution of the words
fdist = FreqDist(tokens)

# create a dictionary to hold the n-gram model
model = defaultdict(lambda: defaultdict(int))

# set the length of the n-grams
n = 3

# create the n-grams and count the frequency of each
for i in range(len(tokens)-n):
    ngram = ' '.join(tokens[i:i+n])
    next_word = tokens[i+n]
    model[ngram][next_word] += 1

# predict the next word
def predict_next_word(text):
    text = text.lower()
    words = text.split()
    ngram = ' '.join(words[-n:])
    if ngram in model:
        return max(model[ngram], key=model[ngram].get)
    else:
        return ""

# example usage
text = "She was walking down the"
next_word = predict_next_word(text)
print(next_word)
