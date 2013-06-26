from tweepy.streaming import StreamListener
from tweepy import OAuthHandler
from tweepy import Stream
from OSC import OSCClient, OSCMessage
import re

# Go to http://dev.twitter.com and create an app.
# The consumer key and secret will be generated for you after
consumer_key=""
consumer_secret=""

# After the step above, you will be redirected to your app's page.
# Create an access token under the the "Your access token" section
access_token=""
access_token_secret=""

client = OSCClient()
client.connect( ("localhost", 11011) )

class StdOutListener(StreamListener):
    """ A listener handles tweets are the received from the stream.
    This is a basic listener that just prints received tweets to stdout.

    """
    def on_data(self, data):
		fields = data.split(',')
		for element in fields:
			if re.search('text',element):
				if len(element.split(':')[0]) < 7:
					Text = element.split(':')[1][1:-1]
					print Text
					msg = OSCMessage()
					msg.setAddress("/print")
					msg.append(Text)
					client.send(msg)
		
		return True

    def on_error(self, status):
        print status

if __name__ == '__main__':
    l = StdOutListener()
    auth = OAuthHandler(consumer_key, consumer_secret)
    auth.set_access_token(access_token, access_token_secret)
	
    stream = Stream(auth, l)
    stream.filter(track=['Alien'])
