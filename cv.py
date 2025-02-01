from inference_sdk import InferenceHTTPClient

CLIENT = InferenceHTTPClient(
    api_url="https://classify.roboflow.com",
    api_key="CkhjQfsI83zbT2waSVjo"
)

def get_plant_health(img):

    result = CLIENT.infer(img, model_id="plant-health-ed1ju/1")

    health = result["top"]
    confidence = result["confidence"]

    return health, confidence

tup = get_plant_health("plant_img.jpeg")

health = (tup[0])
confidence = (tup[1])*100

print(health)
print(confidence)
