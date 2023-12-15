import os
def play_youtube_video(video_id):
    os.system(f"chromium-browser https://youtu.be/CcvdFVeIs-E?si=ZO4bX0waC1Cm9XW4")

def main():
    youtube_video_id = ''ZO4bX0waC1Cm9XW4' # Замените нафактический идентификатор видео с YouTube
    play_youtube_video(youtube_video_id)

if __name__ == "__main__":
    main()