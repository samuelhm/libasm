(function() {
	'use strict';

	var content = document.getElementById('tab-content');
	var buttons = document.querySelectorAll('.tab-btn');
	var cache = {};
	var currentTab = null;

	function extractBody(html) {
		var parser = new DOMParser();
		var doc = parser.parseFromString(html, 'text/html');
		var body = doc.body;
		if (!body) return '';
		var children = body.childNodes;
		var result = '';
		for (var i = 0; i < children.length; i++) {
			result += children[i].outerHTML || children[i].textContent || '';
		}
		return result;
	}

	function loadTab(tab) {
		if (currentTab === tab) return;
		currentTab = tab;

		for (var i = 0; i < buttons.length; i++) {
			if (buttons[i].getAttribute('data-tab') === tab) {
				buttons[i].classList.add('active');
			} else {
				buttons[i].classList.remove('active');
			}
		}

		if (cache[tab]) {
			content.innerHTML = cache[tab];
			window.scrollTo(0, 0);
			return;
		}

		content.innerHTML = '<div class="tab-loading">Cargando contenido...</div>';

		fetch(tab + '.html')
			.then(function(r) {
				if (!r.ok) throw new Error('Error ' + r.status);
				return r.text();
			})
			.then(function(html) {
				cache[tab] = extractBody(html);
				if (currentTab === tab) {
					content.innerHTML = cache[tab];
					window.scrollTo(0, 0);
				}
			})
			.catch(function(err) {
				content.innerHTML = '<div class="tab-error">Error al cargar: ' + err.message + '</div>';
			});
	}

	for (var i = 0; i < buttons.length; i++) {
		buttons[i].addEventListener('click', function() {
			loadTab(this.getAttribute('data-tab'));
		});
	}

	loadTab('common');
})();
