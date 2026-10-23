.pragma library

var extensionsMap = {};

function loadConfig(jsonConfig) {
  extensionsMap = jsonConfig;
}

function getType(ext) {
	ext = ext.toLowerCase().trim();
	if (!ext) return "folder";

	for (var category in extensionsMap) {
		var list = extensionsMap[category];

		if (Array.isArray(list) && list.indexOf(ext) !== -1) {
			return category;
		}
	}

	return "unknown";
}

function addExtension(category, ext) {
	if (!extensionsMap[category]) {
		extensionsMap[category] = [];
	}

	if (extensionsMap[category].indexOf(ext) === -1) {
		extensionsMap[category].push(ext);
	}
}