mkdir -p ~/.config/systemd/user/

cp of_top_track.service  ~/.config/systemd/user/

systemctl --user daemon-reload
systemctl --user disable of_top_track.service
systemctl --user enable of_top_track.service
