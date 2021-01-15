/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/rp_widget.h"
#include "ui/widgets/menu/menu_item_base.h"

namespace Ui {
class MediaSlider;
} // namespace Ui

namespace Calls {

namespace Group {
struct MuteRequest;
struct VolumeRequest;
struct ParticipantState;
} // namespace Group

class MenuVolumeItem final : public Ui::Menu::ItemBase {
public:
	MenuVolumeItem(
		not_null<RpWidget*> parent,
		const style::Menu &st,
		rpl::producer<Group::ParticipantState> participantState,
		int startVolume,
		int maxVolume,
		bool muted);

	not_null<QAction*> action() const override;
	bool isEnabled() const override;

	[[nodiscard]] rpl::producer<bool> toggleMuteRequests() const;
	[[nodiscard]] rpl::producer<bool> toggleMuteLocallyRequests() const;
	[[nodiscard]] rpl::producer<int> changeVolumeRequests() const;
	[[nodiscard]] rpl::producer<int> changeVolumeLocallyRequests() const;

protected:
	int contentHeight() const override;

private:
	void setCloudVolume(int volume);
	void setSliderVolume(int volume);

	const int _maxVolume;
	int _cloudVolume = 0;
	bool _waitingForUpdateVolume = false;
	bool _cloudMuted = false;
	bool _localMuted = false;

	const base::unique_qptr<Ui::MediaSlider> _slider;
	const not_null<QAction*> _dummyAction;
	const style::font &_font;

	rpl::event_stream<bool> _toggleMuteRequests;
	rpl::event_stream<bool> _toggleMuteLocallyRequests;
	rpl::event_stream<int> _changeVolumeRequests;
	rpl::event_stream<int> _changeVolumeLocallyRequests;

};

} // namespace Calls