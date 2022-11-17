import requests
# response = requests.get("https://pokeapi.co/api/v2/pokemon?limit=525")
# poke_map = response.json()
# name_list = []
# for i in poke_map['results']:
#     name_list.append(i["name"])
#     response_url = requests.get(i["url"])
#     json_map = response_url.json()

# def fetch_from_pokeUrl(url):
#     l = []
#     response_url = requests.get(url)
#     json_map = response_url.json()
#     for i in json_map:
#         pass
    
last = [{
    "name" : "bublasaur",
    "baseStats": [1, 1, 1, 1, 1 , 1]
},
{
    "name" : "charizard",
    "baseStats": [1, 1, 1, 1, 1 , 1]
}]

for i in last:
    print(i)