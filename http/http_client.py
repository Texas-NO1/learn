import requests
import json
url = 'http://localhost:8080/body_test'
pid = "id005b8cad-32d1-4740-93e0-9c641ffb611dt"
cids = ["ch18ce8b6f-a0dd-42bb-844e-553e16cb12b8","ch197a3884-c3ed-49ff-8c23-49d704cb2c0c","ch1e2d47be-7cd9-4528-b2fc-c66b8e565aab"]
i = 0
max=3
new_cids = []
while i <= max:
    new_cids.extend(cids)
    i += 1
date = '20231119'
data={"pid": pid, "cids": ','.join(new_cids), "date": date}
# data=json.dumps(data)等价于json=data; data=data等价于params=data; params会解析成url，而url最大长度为8kb(8192)
res=requests.post(url, data=json.dumps(data)) # data作为body，不限制长度
# res=requests.post(url, json=data) # data作为body，不限制长度
# res=requests.post(url, data=data) # data作为url的params，可能会超长
# res=requests.post(url, params=data) # data作为url的params，可能会超长
print(res.status_code)
print(res.text)
