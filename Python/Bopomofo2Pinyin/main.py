mydict = {
    'ㄅ': 'b',
    'ㄆ': 'p',
    'ㄇ': 'm',
    'ㄈ': 'f',
    'ㄪ': 'v',
    'ㄉ': 'd',
    'ㄊ': 't',
    'ㄋ': 'n',
    'ㄌ': 'l',
    'ㄍ': 'g',
    'ㄎ': 'k',
    'ㄫ': 'ng',
    'ㄏ': 'h',
    'ㄐ': 'j',
    'ㄑ': 'q',
    'ㄬ': 'gn',
    'ㄒ': 'x',
    'ㄓ': 'zh',
    'ㄔ': 'ch',
    'ㄕ': 'sh',
    'ㄖ': 'r',
    'ㄗ': 'z',
    'ㄘ': 'c',
    'ㄙ': 's',
    'ㄚ': 'a',
    'ㄛ': 'o',
    'ㄜ': 'e',
    'ㄝ': 'ê',
    'ㄞ': 'ai',
    'ㄟ': 'ei',
    'ㄠ': 'ao',
    'ㄡ': 'ou',
    'ㄢ': 'an',
    'ㄣ': 'en',
    'ㄤ': 'ang',
    'ㄥ': 'eng',
    'ㄦ': 'er',
    '丨': 'i',
    'ㄧ': 'i',
    'ㄨ': 'u',
    'ㄩ': 'ü',
}

buffer = input()
obuffer = ''
ignoreList = ['ˉ', 'ˊ', 'ˇ', 'ˋ', '·', '˙']

for item in buffer:
    if item in mydict.keys():
        obuffer = obuffer + mydict[item]
    elif item in ignoreList:
        obuffer = obuffer + '_'
    else:
        obuffer = obuffer + item

print(obuffer)